import struct, os

MAXFILES = 16


file_names = [
    f for f in os.listdir("user/build")
    if os.path.isfile(os.path.join("user/build", f))
]

numfiles = len(file_names)
file_sizes = []
contents = []
for f in file_names:
    full_path = os.path.join("user/build", f)
    file_sizes.append(os.path.getsize(full_path))
    with open(full_path, "rb") as fin:
        contents.append(fin.read())

file_sizes.extend(0 for _ in range(MAXFILES - len(file_sizes)))
file_names.extend("" for _ in range(MAXFILES - len(file_names)))


with open("build/filesystem.bin", "wb") as f:
    f.write(struct.pack("<I", numfiles))
    
    for size in file_sizes:
        f.write(struct.pack("<I", size))

    for name in file_names:
        name_bytes = name.encode('ascii')[:10]  # take at most 10 bytes
        name_padded = name_bytes.ljust(11, b'\x00')  # pad up to 10 bytes
        f.write(name_padded)

    for content in contents:
        f.write(content)


    

    
