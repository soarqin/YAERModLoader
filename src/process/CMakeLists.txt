add_project(process STATIC
    image.c image.h
    scanner.c scanner.h
    cpu_affinity.c cpu_affinity.h
    util.c util.h
    FOLDER libs
)
