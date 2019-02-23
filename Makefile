JAVAC=javac
sources = $(wildcard src/*.java)
classes = $(sources:.java=.class)

all: myProgram jar

myProgram: $(classes)

%.class: %.java
	$(JAVAC) $<

jar:    
	@echo "Manifest-Version: 1.0" > manifest.txt
	@echo "Class-Path: ." >> manifest.txt
	@echo "Main-Class: Main" >> manifest.txt
	@echo "" >> manifest.txt

	jar -cmf manifest.txt JARNAME.jar $(classes)

clean:
	rm -f *.class
	rm manifest.txt
