JAVAC=javac
sources = $(wildcard *.java)
classes = $(sources:.java=.class)

all: myProgram jar copy_file

myProgram: $(classes)

%.class: %.java
	$(JAVAC) $<

jar:    
	@echo "Manifest-Version: 1.0" > manifest.txt
	@echo "Class-Path: ." >> manifest.txt
	@echo "Main-Class: Main" >> manifest.txt
	@echo "" >> manifest.txt

	jar -cmf manifest.txt runTM.jar $(classes)

copy_file:
	chmod +x exe_tm.sh
	cp exe_tm.sh runtm
	chmod +x runtm

clean:
	rm -rf *.class
	rm manifest.txt
	rm runTM.jar
	rm runtm
