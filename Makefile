.PHONY: clean all nx pc run netload netload_quiet docs

all: nx pc

pc:
	@make -f Makefile.pc

run:
	@make run -f Makefile.pc

nx:
	@make -f Makefile.nx

netload:
	@make nxs -f Makefile.nx

netload_quiet:
	@make nx -f Makefile.nx

clean:
	@make clean -f Makefile.nx
	@make clean -f Makefile.pc

docs:
	@doxygen Doxyfile
