# Find gnulib headers.
ACLOCAL_AMFLAGS = -I m4

# Subdirectories to descend into.
SUBDIRS = src

dist_doc_DATA = README

clean-local:
	find . -name "*~" -delete
	find . -name "*#" -delete
	rm -f compile ar-lib depcomp install-sh libtool ltmain.sh missing
