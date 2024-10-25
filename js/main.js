

document.getElementById('btnGuardar').onclick = async function (e) {
    e.preventDefault();

    n = document.getElementById('nombre').value;
    a = document.getElementById('apellido').value;
    c = document.getElementById('confColor').value;
    orden = "guardar";
    
    response = await fetch(`/cgi-bin/funciones.cgi`,{
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: new URLSearchParams({
            'nombre':n,
            'apellido':a,
            'color':c,
            'orden':orden
        })
    });
    data = await response.text();
    
    document.getElementById('resultado').innerHTML = decodeURI(data);
    
};


document.getElementById('btnCargar').onclick = async function (e) {
    e.preventDefault();

    orden = "cargar";
    
    response = await fetch(`/cgi-bin/funciones.cgi`,{
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: new URLSearchParams({
            'orden':orden
        })
    });
    data = await response.json();
    
    document.getElementById('nombre').value = decodeURI(data.nombre);
    document.getElementById('apellido').value = decodeURI(data.apellido);
    document.getElementById('confColor').value = decodeURIComponent(data.color);
    document.getElementById('idBody').style.backgroundColor = decodeURIComponent(data.color);
    document.getElementById('resultado').innerHTML = decodeURI(data.mensaje);
    
};