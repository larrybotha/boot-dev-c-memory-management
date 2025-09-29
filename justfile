default:
  @just --list

build in out deps="":
  zig cc {{ in }} {{deps}} -o {{ out }}

watch in deps="" out="tmp":
  #!/usr/bin/env bash

  set -euo pipefail

  name=$(basename $(dirname "{{ in }}"))
  dest="{{ out }}/${name}"

  watchexec --clear --exts c,h \
    "just build {{ in }} ${dest} '{{ deps }}' && echo '' && ./${dest}"

ch-01-19:
  just watch 01/19-sizeof/main.c

ch-02-01:
  just watch 02/01-structs/main.c munit/munit.c

ch-03-05:
  just watch 03/05-why-pointers/main.c \
    "03/05-why-pointers/coordinate.c munit/munit.c"

ch-03-06:
  just watch 03/06-pointer-basics/main.c \
    "03/06-pointer-basics/exercise.c munit/munit.c"

ch-03-09-test:
  just watch 03/09-arrays-as-pointers/test.c \
    "munit/munit.c"

ch-03-09-example:
  just watch 03/09-arrays-as-pointers/example.c

ch-03-11:
  just watch 03/11-array-casting/main.c

ch-03-13:
  just watch 03/13-arrays-decay-to-pointers/main.c
