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
