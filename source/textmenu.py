import re
import sys

header_name = "menu_utils.h"
menu_type = "MENU_menu_type"
entry_type = "MENU_menu_entry_type"
back_handler = "MENU_backHandler"
exit_handler = "MENU_exitHandler"
end_handler = "MENU_endHandler"
handle_def = "MENU_handler"

ignore_escaped = "(?<!\\\)"


def malloc_string(data_type, variable_name, number, initialization=False):
    output = data_type \
             + " *" + variable_name + " = (" + data_type + "*) " \
             + "malloc( sizeof(" + data_type + ") * " + str(number) + " );\n"

    if initialization:
        return output
    else:
        return output[output.find(" ") + 2::]


def indent_text(text):
    indented_text = ""
    next_indent_level = 0

    for line in text.split("\n"):
        curr_indent_level = next_indent_level

        if not (("{" in line) and ("}" in line)):
            if "{" in line:
                next_indent_level = curr_indent_level + 1
            if "}" in line:
                curr_indent_level -= 1
                next_indent_level = curr_indent_level

        indented_text += "    " * curr_indent_level + line + "\n"

    return indented_text


def parse_file(filename):
    input_f = open(filename)

    entry_index = 0
    result = [["ROOT", ""]]
    index_stack = []

    capturing_text = True
    entry_text = ""

    for line in input_f:
        line = line.strip()

        if re.search(ignore_escaped + "{", line):
            index_stack.append(entry_index)
            capturing_text = False

            result[len(result) - 1].append(entry_text)

            entry_text = ""

        elif re.search(ignore_escaped + "}", line):
            index_stack.pop()

        elif re.search(ignore_escaped + "\\[", line):
            entry_index += 1
            result.append([index_stack[len(index_stack) - 1],
                           line[0:line.find("[")] + "\n",
                           line[line.find("[") + 1:line.find("]")].replace(" ", ""),
                           "#!FUNCTION_MARKER"])

        elif re.search(ignore_escaped + ":", line):
            entry_index += 1
            capturing_text = True
            result.append([index_stack[len(index_stack) - 1],
                           line[0:-1] + "\n"])

        elif capturing_text:
            entry_text += line.replace("\\", "") + "\n"

    input_f.close()

    return result


if __name__ == "__main__":
    input_filename = ""
    output_filename = ""

    if len(sys.argv) != 4:
        print("USAGE: textmenu.py input_file output_file desired_menu_name")
        exit()

    input_filename = sys.argv[1]
    output_filename = sys.argv[2]
    menu_name = sys.argv[3]

    try:
        entry_list = parse_file(input_filename)
    except:
        print("Unable to open file for reading")
        exit()

    # calculate unique menu indices and entries in each menu
    enumerated_entries = [(entry, i) for i, entry in enumerate(entry_list)]
    menu_entries = [entry for entry in enumerated_entries if "#!FUNCTION_MARKER" not in entry[0]]

    # entry index => menu index
    entry_to_menu = {menu[1]: i for i, menu in enumerate(menu_entries)}

    # calculate entry count of every menu
    menu_lengths = [0] * len(menu_entries)
    for entry in enumerated_entries[1::]:
        menu_lengths[entry_to_menu[entry[0][0]]] += 1

    # exclude root
    entry_list = entry_list[1::]

    # list of menu welcome strings
    welcome_strings = [entry[0][2] for entry in menu_entries]
    entry_names = [entry[1] for entry in entry_list]

    # form list of handler pointers
    handler_list = []
    for entry in entry_list:
        if "#!FUNCTION_MARKER" in entry:
            handler_list.append(entry[2])
        else:
            handler_list.append("NULL")

    # which entry belongs to which menu
    root_menu_indexes = [entry_to_menu[entry[0]] for entry in entry_list]

    menu_count = str(len(menu_entries))
    entry_count = str(len(entry_list))

    # start generating code
    output_text = ""
    output_text += "#include \"" + header_name + "\"\n\n"
    output_text += "// MACHINE-GENERATED FILE, DO NOT CHANGE\n"
    output_text += menu_type + "* MENU_initialize_" + menu_name + "() {\n"

    output_text += "const int menu_sizes[" + menu_count + "] = " \
                   + "{" + str([menu for menu in menu_lengths])[1:-1] + "};\n"
    output_text += "int entry_counters[" + menu_count + "] = " \
                   + "{" + "0, " * (int(menu_count) - 1) + "0 };\n"
    output_text += "const int string_lengths[" + menu_count + "] = " \
                   + "{" + str([len(string) + 1 for string in welcome_strings])[1:-1] + "};\n"

    output_text += "const int entry_name_lengths[" + entry_count + "] = " \
                   + "{" + str([len(string) + 1 for string in entry_names])[1:-1] + "};\n"

    output_text += "const " + handle_def + " handlers[" + str(len(handler_list)) + "] = " \
                   + "{" + str([string for string in handler_list])[1:-1].replace("'", "") + "};\n"
    output_text += "const int root_menu_ptrs[" + str(len(handler_list)) + "] = " \
                   + "{" + str([idx for idx in root_menu_indexes])[1:-1] + "};\n\n"

    output_text += "int menu_ptr = 1;\n\n"

    output_text += malloc_string(menu_type, "menu", len(menu_lengths), True)
    output_text += malloc_string(entry_type, "entries", len(entry_list), True)

    output_text += "\n"

    output_text += "for( int i = 0; i < " + menu_count + "; i++ ) {\n"
    output_text += malloc_string(entry_type + "*", "menu[i].entries", 0, False).replace("0", "(menu_sizes[i] + 1)")
    output_text += malloc_string("char", "menu[i].welcome_string", 0).replace("0", "string_lengths[i]")
    output_text += "menu[i].entries[menu_sizes[i]] = NULL;\n"
    output_text += "}\n\n"

    for i, string in enumerate(welcome_strings):
        output_text += "memcpy( menu[" + str(i) + "].welcome_string, " + \
                       "\"" + string.replace("\n", "\\n") + "\", " \
                       + "string_lengths[" + str(i) + "] );\n"

    output_text += "\n"

    output_text += "for( int i = 0; i < " + entry_count + "; i++ ) {\n"
    output_text += malloc_string("char", "entries[i].string", 0).replace("0", "entry_name_lengths[i]")
    output_text += "menu[root_menu_ptrs[i]].entries[entry_counters[root_menu_ptrs[i]]++] = &entries[i];\n"
    output_text += "if( handlers[i] == NULL ) {\n"
    output_text += "menu[menu_ptr].prev_menu = &menu[root_menu_ptrs[i]];\n"
    output_text += "entries[i].next_menu = &menu[menu_ptr++];\n"
    output_text += "entries[i].handler = NULL;\n"
    output_text += "}\n"
    output_text += "else {\n"
    output_text += "entries[i].next_menu = NULL;\n"
    output_text += "entries[i].handler = handlers[i];\n"
    output_text += "}\n"
    output_text += "}\n\n"

    for i, string in enumerate(entry_names):
        output_text += "memcpy( entries[" + str(i) + "].string, " + \
                       "\"" + string.replace("\n", "\\n") + "\", " \
                       + "entry_name_lengths[" + str(i) + "] );\n"

    output_text += "\n"
    output_text += "menu[0].prev_menu = NULL;\n"
    output_text += "return &menu[0];\n"
    output_text += "}"

    output_text = indent_text(output_text)

    #print(output_text)

    try:
        output_f = open(output_filename, "w")
        output_f.write(output_text)
        output_f.close()
    except:
        print("Unable to open file for writing")
        exit()

    print("Parsed successfully")
