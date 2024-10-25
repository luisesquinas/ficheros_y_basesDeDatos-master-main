EJECUTABLE = .\cgi-bin\funciones.cgi
ARCHIVOS = .\cgi-bin\funciones.cpp
LIBRERIAS = -lnetapi32
PUERTO = 8000

all: elimina_cgi compila abre_navegador abre_servidor

elimina_cgi:
	del $(EJECUTABLE)

compila: $(ARCHIVOS)
	g++ -o $(EJECUTABLE) $(ARCHIVOS) 

abre_servidor:
	python -m http.server --cgi $(PUERTO)

abre_navegador:
	cmd /c start http://localhost:$(PUERTO)
