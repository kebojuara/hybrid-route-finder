const map = L.map('map')
    .setView(
        [-7.2795, 112.7900],
        15
    );

L.tileLayer(
    'https://tile.openstreetmap.org/{z}/{x}/{y}.png',
    {
        maxZoom: 19
    }
).addTo(map);

let routeLine = null;

let startMarker = null;
let endMarker = null;

let selectingStart = true;

map.on(
    "click",
    function(e)
    {
        const lat =
            e.latlng.lat;

        const lon =
            e.latlng.lng;

        if (selectingStart)
        {
            if (startMarker)
            {
                map.removeLayer(
                    startMarker);
            }

            startMarker =
                L.marker(
                    [lat, lon])
                .addTo(map)
                .bindPopup(
                    "Start Point");

            document
                .getElementById(
                    "startLat")
                .value = lat;

            document
                .getElementById(
                    "startLon")
                .value = lon;

            selectingStart = false;
        }
        else
        {
            if (endMarker)
            {
                map.removeLayer(
                    endMarker);
            }

            endMarker =
                L.marker(
                    [lat, lon])
                .addTo(map)
                .bindPopup(
                    "Destination");

            document
                .getElementById(
                    "endLat")
                .value = lat;

            document
                .getElementById(
                    "endLon")
                .value = lon;

            selectingStart = true;
        }
    });