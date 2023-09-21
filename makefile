# Nom de votre exécutable
TARGET = projetC1

# Flags pour le compilateur et l'édition de liens
CFLAGS = -g -O2 -Wall `pkg-config --cflags MLV`
LDFLAGS = `pkg-config --libs-only-other --libs-only-L MLV`
LDLIBS = `pkg-config --libs-only-l MLV`

# Fichiers source
SOURCES = main.c functions.c
HEADERS = functions.h

# Règles pour créer l'exécutable
$(TARGET): $(SOURCES) $(HEADERS)
	gcc $(SOURCES) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(TARGET)

# Règle pour nettoyer les fichiers générés
clean:
	-rm -f $(TARGET)
