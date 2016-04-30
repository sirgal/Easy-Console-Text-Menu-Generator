import re
import sys

header_name = "ectmg_utils.h"
menu_type = "ECTMG_menu_t"
entry_type = "ECTMG_menu_entry_t"
back_handler = "ECTMG_backHandler"
exit_handler = "ECTMG_exitHandler"
end_handler = "ECTMG_endHandler"
handle_def = "ECTMG_handler"
STRING_C_TYPE = "char*"

ignore_escaped = "(?<!\\\)"


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

    name_prefix = "ECTMG_" + menu_name
    all_entries = name_prefix + "_all_entries"
    instance = name_prefix + "_instance"

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

    # which menu has which entry
    entries_in_menu = [[i for i, x in enumerate(root_menu_indexes) if x == j] for j in range(len(menu_entries))]

    # stringify for later use
    menu_count = str(len(menu_entries))
    entry_count = str(len(entry_list))

    # start generating code
    code = ""
    code += "#include \"" + header_name + "\"\n\n"
    code += "// MACHINE-GENERATED FILE, DO NOT CHANGE\n"

    # static menu and menu entry instances
    code += menu_type + " " + instance + "[" + menu_count + "];\n"
    code += entry_type + " " + all_entries + "[" + entry_count + "];\n\n"

    # strings
    static_strings = [("welcome", welcome_strings), ("entry", entry_names)]
    string_names = lambda name, i: name_prefix + "_" + name + "_string_" + str(i)

    for string_type, strings in static_strings:
        for i, string in enumerate(strings):
            string = string.replace("\n", "\\n") 
            code += STRING_C_TYPE + " " + string_names(string_type, i) + " = \"" + string + "\";\n"

        code += "\n"

        code += STRING_C_TYPE + " " + name_prefix + "_" + string_type + "_strings[] = {\n"
        code += ",\n".join([string_names(string_type, i) for i in range(len(strings))])
        code += "\n};\n\n"

    # menus and their entries
    entry_names = lambda i: name_prefix + "_entry_" + str(i)
    for i, entries in enumerate(entries_in_menu):
        entries = list(map(lambda x: "&" + all_entries + "[" + str(x) + "]", entries))
        entries += ["NULL"]
        code += entry_type + "* " + entry_names(i) + "[" + str(menu_lengths[i] + 1)
        code += "] = {" + ", ".join(entries) + "};\n"

    code += "\n"
    code += entry_type + "** " + name_prefix + "_menu_entries[] = {\n"
    code += ",\n".join([entry_names(i) for i in range(len(menu_entries))])
    code += "\n};\n\n"

    # initialization function
    code += menu_type + "* ECTMG_initialize_" + menu_name + "() {\n"

    # handler functions
    code += "const " + handle_def + " handlers[" + str(len(handler_list)) + "] = "
    code += "{" + str([string for string in handler_list])[1:-1].replace("'", "") + "};\n"
    # root menu pointers
    code += "const int root_menu_ptrs[" + str(len(handler_list)) + "] = "
    code += "{" + str([idx for idx in root_menu_indexes])[1:-1] + "};\n\n"
    # submenu counter
    code += "int menu_ptr = 1;\n\n"

    # menu instances pointers initialization
    code += "for( int i = 0; i < " + menu_count + "; i++ ) {\n"
    code += instance + "[i].entries = " + name_prefix + "_menu_entries[i];\n"
    code += instance + "[i].welcome_string = " + name_prefix + "_welcome_strings[i];\n"
    code += "}\n\n"

    # menu entries handlers initialization
    code += "for( int i = 0; i < " + entry_count + "; i++ ) {\n"
    code += all_entries + "[i].string = " + name_prefix + "_entry_strings[i];\n"
    code += "if( handlers[i] == NULL ) {\n"
    code += instance + "[menu_ptr].prev_menu = &" + instance + "[root_menu_ptrs[i]];\n"
    code += all_entries + "[i].next_menu = &" + instance + "[menu_ptr++];\n"
    code += all_entries + "[i].handler = NULL;\n"
    code += "}\n"
    code += "else {\n"
    code += all_entries + "[i].next_menu = NULL;\n"
    code += all_entries + "[i].handler = handlers[i];\n"
    code += "}\n"
    code += "}\n\n"

    # root setup and return
    code += instance + "[0].prev_menu = NULL;\n"
    code += "return &" + instance + "[0];\n"
    code += "}"

    code = indent_text(code)

    try:
        output_f = open(output_filename, "w")
        output_f.write(code)
        output_f.close()
    except:
        print("Unable to open file for writing")
        exit()

    print("Parsed successfully")
