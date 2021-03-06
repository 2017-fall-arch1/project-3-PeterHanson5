all:
	(cd timerLib; make install)
	(cd lcdLib; make install)
	(cd shapeLib; make install)
	(cd circleLib; make install)
	(cd p2swLib; make install)
	(cd snakeyGame; make)

load: all
	(cd snakeyGame; make load)

doc:
	rm -rf doxygen_docs
	doxygen Doxyfile
clean:
	(cd timerLib; make clean)
	(cd lcdLib; make clean)
	(cd shapeLib; make clean)
	(cd p2swLib; make clean)
	(cd snakeyGame; make clean)
	(cd circleLib; make clean)
	rm -rf lib h
	rm -rf doxygen_docs/*
