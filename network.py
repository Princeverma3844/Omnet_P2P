# Define the filename
file_path = "C:/Users/Public/omnetpp-6.0.3-windows-x86_64/omnetpp-6.0.3/samples/assign3/Network.ned"

file_path1 = "C:/Users/Public/omnetpp-6.0.3-windows-x86_64/omnetpp-6.0.3/samples/assign3/client.ned"
file_path2 = "C:/Users/PRINCE VERMA/Desktop/value.txt"
file_path3 = "C:/Users/PRINCE VERMA/Desktop/value1.txt"

# Read the content of the file
with open(file_path, 'r') as file:
    content = file.read()

with open(file_path1, 'r') as file:
    content1 = file.read()

with open(file_path2, 'r') as file:
    content2 = file.read()

with open(file_path3, 'r') as file:
    content3 = file.read()

# Take input from the user for the new value of n
new_value_of_n = int(input("Enter the new value for n: "))

temp = new_value_of_n
m = 0
while(temp > 0):
    m = m + 1
    temp = temp//2

# Modify the value of n in the content
content = content.replace(f'int n = {content2}', f'int n = {new_value_of_n}')
content = content.replace(f'int m = {content3}', f'int m = {m}')
content1 = content1.replace(f'int n = {content2}', f'int n = {new_value_of_n}')
content1 = content1.replace(f'int m = {content3}', f'int m = {m}')

# Write the modified content back to the file
with open(file_path, 'w') as file:
    file.write(content)

with open(file_path1, 'w') as file:
    file.write(content1)

with open(file_path2, 'w') as file:
    file.write(f"{new_value_of_n}")

with open(file_path3, 'w') as file:
    file.write(f"{m}")

print(f'Successfully changed the values')
