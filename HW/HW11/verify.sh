#!/bin/bash
[[ $(sha512sum my_malloc.h | cut -d " " -f 1) == 4f029a2b5378b5787d291f78c9c3e5490b6ea04a5c7f05781946bd6685caef7cfd31befff5a503f2f57a686a5e1ff16be722681f162a1ee61b72786b208a9f29 ]] || { printf 'error: my_malloc.h was modified! re-download it and try again\n' >&2; exit 1; }
