var m; // mapa
var popupId;
var infoBox    = [];
var marcadores = [];

function inicializar() {

	var opcoes = {
        zoom: 7,
		center: { lat: -28.8800397, lng: -49.0587899 },
        mapTypeId: google.maps.MapTypeId.ROADMAP
    };

	m = new google.maps.Map(document.getElementById("mapa"), opcoes);
	
}

inicializar();

function abrirInformacoes(identificador, marcador) {

	if (typeof(popupId) == 'number' && typeof(infoBox[popupId]) == 'object') {
		infoBox[popupId].close();
	}

	infoBox[identificador].open(m, marcador);
	popupId = identificador;

}

function carregarMarcadores() {
	
	$.getJSON('js/dadosFechados.json', function(pontos) {
		
		var area = new google.maps.LatLngBounds();
		
		$.each(pontos, function(index, infoCoordenada) {
			
			var marcador = new google.maps.Marker({
				position: new google.maps.LatLng(infoCoordenada.Latitude, infoCoordenada.Longitude),
				title: "Clique aqui!",
				icon: 'img/marcador.png'
			});
			
			var myOptions = {
				content: "<p>Temperatura: "     + infoCoordenada.Temperatura  + "</br>" +
						    "Pluviômetro: "     + infoCoordenada.Pluviometro  + "</br>" +
						    "Umidade do ar: "   + infoCoordenada.UmidadeAr    + "</br>" +
						    "Anemômetro: "      + infoCoordenada.Anemometro   + "</br>" +
						    "Luminosidade: "    + infoCoordenada.Luminosidade + "</br>" +
						    "Radiação do sol: " + infoCoordenada.RadiacaoSol  + "</p>",
							
				pixelOffset: new google.maps.Size(-150, 0)
        	};

			infoBox[infoCoordenada.Id] = new InfoBox(myOptions);
			infoBox[infoCoordenada.Id].marcador = marcador;
			
			infoBox[infoCoordenada.Id].listener = google.maps.event.addListener(marcador, 'click', function (e) {
				abrirInformacoes(infoCoordenada.Id, marcador);
			});
			
			marcadores.push(marcador);
			
			area.extend(marcador.position);
			
		});
		
		var marcadoresAgrupados = new MarkerClusterer(m, marcadores, {imagePath: 'https://developers.google.com/maps/documentation/javascript/examples/markerclusterer/m'});
		
		m.fitBounds(area);
		
	});
	
}

carregarMarcadores();