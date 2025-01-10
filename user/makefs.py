import struct, os


file_names = [
    f for f in os.listdir("user/elf")
    if os.path.isfile(os.path.join("user/elf", f))
]
numfiles = len(file_names)
file_sizes = []
contents = []
for f in file_names:
    full_path = os.path.join("user/elf", f)
    file_sizes.append(os.path.getsize(full_path))
    with open(full_path, "rb") as fin:
        contents.append(fin.read())

file_sizes.extend(0 for _ in range(16 - len(file_sizes)))
file_names.extend("" for _ in range(16 - len(file_names)))


with open("build/filesystem_header.bin", "wb") as f:
    f.write(struct.pack("<I", numfiles))
    
    for size in file_sizes:
        f.write(struct.pack("<I", size))

    for name in file_names:
        name_bytes = name.encode('ascii')[:10]  # take at most 10 bytes
        name_padded = name_bytes.ljust(10, b'\x00')  # pad up to 10 bytes
        f.write(name_padded)

    for content in contents:
        f.write(content)


    

    
