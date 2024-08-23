dependency:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graphImage.png

prepare:
	rm -rf build docs
	mkdir build docs

install:
	sudo apt-get install gcovr lcov

install_doc:
	pip install jinja2 Pygments
	sudo apt-get install doxygen
