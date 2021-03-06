 # Copyright 2004 Apache Software Foundation
 #
 #  Licensed under the Apache License, Version 2.0 (the "License");
 #  you may not use this file except in compliance with the License.
 #  You may obtain a copy of the License at
 #
 #      http://www.apache.org/licenses/LICENSE-2.0
 #
 #  Unless required by applicable law or agreed to in writing, software
 #  distributed under the License is distributed on an "AS IS" BASIS,
 #  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 #  See the License for the specific language governing permissions and
 #  limitations under the License.
 #
 # Originally developed by Gregory Trubetskoy.
 #
 #
 # Makefile for mod_python documentation
 # ---------------------------------
 #
 # See also the README file.
 #

# You need to set this manually
# or ./configure --with-python-src=path/to/python/src
PYTHON_SRC=

# This is the *documentation* release, and is used to construct the file
# names of the downloadable tarballs.
RELEASE=	2.7

MKHOWTO=	$(PYTHON_SRC)/Doc/tools/mkhowto

# These must be declared phony since there
# are directories with matching names:
.PHONY: html

# This can be changed to a4
PAPER=		letter

MPFILES=	modpython.tex \
		copyright.tex \
		modpython1.tex \
		modpython2.tex \
		modpython3.tex \
		modpython5.tex \
		modpython6.tex \
		modpython7.tex \
		appendixa.tex \
		appendixb.tex

# this target pukes if we don't have PYTHON_SRC set
src_set:
	@if test -z "$(PYTHON_SRC)"; then \
		echo; \
		echo "Please edit Makefile and set PYTHON_SRC to where Python sources are."; \
		echo; \
		exit 1; \
	fi

# Main target
all:	pdf

dvi:	$(MPFILES) src_set
	$(MKHOWTO) --dvi modpython.tex

pdf:	$(MPFILES) src_set
	$(MKHOWTO) --pdf --$(PAPER) modpython.tex

ps:	$(MPFILES) src_set
	$(MKHOWTO) --ps --$(PAPER) modpython.tex

html:	$(MPFILES) src_set
	$(MKHOWTO) --html modpython.tex
	mkdir -p modpython/icons
	cp $(PYTHON_SRC)/Doc/html/icons/* modpython/icons/
	rm -f modpython/modpython.how
# the iconserver option of mkhowto is broken since it writes
# it to the end if the init_file where they aren't useful anymore,
# so we work around it:
	for f in `find modpython -type f`; do \
	  cat $$f | sed s/\.\.\\/icons/icons/g > $${f}2; \
	  mv $${f}2 $$f; \
	done

world:	ps pdf html tarballs

# Release packaging targets:

pdf-$(PAPER)-$(RELEASE).tgz: pdf
	tar cf - *.pdf | gzip -9 >$@

pdf-$(PAPER)-$(RELEASE).tar.bz2: pdf
	tar cf - *.pdf | bzip2 -9 >$@

pdf-$(PAPER)-$(RELEASE).zip: pdf
	rm -f $@
	zip -q -9 $@ *.pdf

postscript-$(PAPER)-$(RELEASE).tar.bz2: ps
	tar cf - *.ps | bzip2 -9 >$@

postscript-$(PAPER)-$(RELEASE).tgz: ps
	tar cf - *.ps | gzip -9 >$@

postscript-$(PAPER)-$(RELEASE).zip: ps
	rm -f $@
	zip -q -9 $@ *.ps

html-$(RELEASE).tgz:	html
	tar cf - modpython | gzip -9 >$@

html-$(RELEASE).tar.bz2:	html
	tar cf - modpython | bzip2 -9 >$@

html-$(RELEASE).zip:	html
	rm -f $@
	zip -q -9 $@ modpython

# convenience targets:

tarhtml:	html-$(RELEASE).tgz
tarps:		postscript-$(PAPER)-$(RELEASE).tgz
tarpdf:		pdf-$(PAPER)-$(RELEASE).tgz

tarballs:	tarpdf tarps tarhtml

ziphtml:	html-$(RELEASE).zip
zipps:		postscript-$(PAPER)-$(RELEASE).zip
zippdf:		pdf-$(PAPER)-$(RELEASE).zip

zips:		zippdf zipps ziphtml

bziphtml:	html-$(RELEASE).tar.bz2
bzipps:		postscript-$(PAPER)-$(RELEASE).tar.bz2
bzippdf:	pdf-$(PAPER)-$(RELEASE).tar.bz2

bzips:		bzippdf bzipps bziphtml


# Housekeeping targets

# Remove temporary files; all except the following:
# - sources: .tex, .bib, .sty, *.cls
# - useful results: .dvi, .pdf, .ps, .texi, .info
clean:
	rm -f *~ *.aux *.idx *.ilg *.ind *.log *.toc *.bkm *.syn *.pla api.tex

# Remove temporaries as well as final products
clobber:	clean
	rm -rf modpython
	rm -f html-$(RELEASE).tgz
	rm -f pdf-$(RELEASE).tgz postscript-$(RELEASE).tgz
	rm -f html-$(RELEASE).zip
	rm -f pdf-$(RELEASE).zip postscript-$(RELEASE).zip

realclean:  clobber
distclean:  clobber
	rm -f Makefile

# HTML in the doc directory
dist: version html
	rm -rf ../doc-html
	mv modpython ../doc-html

# Version substitution
version: ../src/include/mpversion.h
	DATE="`date +'%B %d, %Y'`"; \
	VERSION="`awk '/MPV_STRING/ {print $$3}' ../src/include/mpversion.h`"; \
	VERSION="`echo $$VERSION | sed s/\\"//g`"; \
	cat modpython.tex | sed "s/\\\release.*/\\\release\{$$VERSION\}/" >modpython.tex2; \
	cat modpython.tex2 | sed s/\\date.*/\\date\{"$$DATE"\}/ >modpython.tex


