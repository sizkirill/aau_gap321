import os

class_name = input('What process would you like to add?\n')
source_dir = '..\\Source\\Logic\\Process\\'

target_dir = input('Which directory should it live in?\n')

target_dir = source_dir + target_dir
clean_target_dir = target_dir.strip('\r')
clean_class = class_name.strip('\r')
create_class = True

dir_exists = os.path.isdir(clean_target_dir)

if not dir_exists:
    print('{0} does not exist\n'.format(clean_target_dir))
    make_dir = input('Would you like to make it?  (y/n)\n').strip('\r')

    if make_dir.lower() == 'y':
        os.mkdir(clean_target_dir)
    else:
        print('Exiting...')
        quit(1)

component_names = list()
components_done = False
while not components_done:
    component_name = input('Enter component that process uses or skip if none more: ').strip(' \n\r')
    if component_name == '':
        components_done = True
    else:
        component_names.append(component_name)

includes = list()
for root, dirs, files in os.walk('..\\Source\\Logic\\Components'):
    for file in files:
        if file.endswith('.h') and file[:-2] in component_names:
            pathToFile = os.path.relpath(os.path.join(root, file))
            includes.append(pathToFile[pathToFile.find('Logic\\'):].replace('\\', '/'))
            print("Found " + file + " in " + os.path.join(root, file))

for root, dirs, files in os.walk('..\\..\\Yangine\\Yangine\\Source\\Logic\\Components'):
    for file in files:
        if file.endswith('.h') and file[:-2] in component_names:
            pathToFile = os.path.relpath(os.path.join(root, file))
            includes.append(pathToFile[pathToFile.find('Logic\\'):].replace('\\', '/'))
            print("Found " + file + " in " + os.path.join(root, file))
            component_names = ['yang::' + x if x == file[:-2] else x for x in component_names]

includes = ['#include <' + x + '>' for x in includes]
component_names_args = [x + '* p' + x[6:] if x.startswith('yang::') else x + '* p' + x for x in component_names]

# -- COPY HEADER --

# Open files
header_file_template = open('../Data/ProcessTemplates/TemplateProcessHeader.txt', 'r')
header_file_copy = open(clean_target_dir + '\\' + clean_class + '.h', 'w')
header_file_data = header_file_template.read()

# Copy data
header_file_data = header_file_data.replace('$process_name', clean_class)
header_file_data = header_file_data.replace('$components_includes', '\n'.join(includes))
header_file_data = header_file_data.replace('$component_names_args', ', '.join(component_names_args))
header_file_data = header_file_data.replace('$component_names', ', '.join(component_names))

# Write data
header_file_copy.write(header_file_data)

# Close files
header_file_copy.close()
header_file_template.close()

print('Copied template to ' + clean_class + ".h")
# -- COPY SOURCE --

# Open files
source_file_template = open('../Data/ProcessTemplates/TemplateProcessCpp.txt', 'r')
source_file_copy = open(clean_target_dir + '\\' + clean_class + '.cpp', 'w')

# Copy data
source_file_data = source_file_template.read()
source_file_data = source_file_data.replace('$process_name', clean_class)
source_file_data = source_file_data.replace('$component_names_args', ', '.join(component_names_args))
source_file_data = source_file_data.replace('$component_names', ', '.join(component_names))

# Write data
source_file_copy.write(source_file_data)

# Close files
source_file_copy.close()
source_file_template.close()
print('Copied template to ' + clean_class + ".cpp")
