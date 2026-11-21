document
    .getElementById("routeBtn")
    .addEventListener(
        "click",
        async () =>
        {
            const startLat =
                parseFloat(
                    document.getElementById(
                        "startLat").value);

            const startLon =
                parseFloat(
                    document.getElementById(
                        "startLon").value);

            const endLat =
                parseFloat(
                    document.getElementById(
                        "endLat").value);

            const endLon =
                parseFloat(
                    document.getElementById(
                        "endLon").value);

            const result =
                await requestRoute(
                    startLat,
                    startLon,
                    endLat,
                    endLon);

            if (!result.success)
            {
                alert(
                    "Route not found");

                return;
            }

            if (routeLine)
            {
                map.removeLayer(
                    routeLine);
            }

            if (startMarker)
            {
                map.removeLayer(
                    startMarker);
            }

            if (endMarker)
            {
                map.removeLayer(
                    endMarker);
            }

            const coordinates =
                result.route.map(
                    point =>
                    [
                        point.lat,
                        point.lon
                    ]);

            routeLine =
                L.polyline(
                    coordinates)
                .addTo(map);

            map.fitBounds(
                routeLine.getBounds());

            startMarker =
                L.marker(
                    coordinates[0])
                .addTo(map);

            endMarker =
                L.marker(
                    coordinates[
                        coordinates.length - 1])
                .addTo(map);

            const distanceKm =
                result.distanceMeters
                / 1000.0;

            const minTime =
                distanceKm
                / 40.0
                * 60.0;

            const maxTime =
                distanceKm
                / 20.0
                * 60.0;

            document
                .getElementById(
                    "distance")
                .innerText =
                distanceKm
                .toFixed(2)
                + " km";

            document
                .getElementById(
                    "time")
                .innerText =
                minTime.toFixed(1)
                + " - "
                + maxTime.toFixed(1)
                + " min";
            
            document
                .getElementById(
                    "resetBtn")
                .addEventListener(
                    "click",
                    () =>
                    {
                        if (startMarker)
                        {
                            map.removeLayer(
                                startMarker);

                            startMarker = null;
                        }

                        if (endMarker)
                        {
                            map.removeLayer(
                                endMarker);

                            endMarker = null;
                        }

                        if (routeLine)
                        {
                            map.removeLayer(
                                routeLine);

                            routeLine = null;
                        }

                        document
                            .getElementById(
                                "startLat")
                            .value = "";

                        document
                            .getElementById(
                                "startLon")
                            .value = "";

                        document
                            .getElementById(
                                "endLat")
                            .value = "";

                        document
                                .getElementById(
                                "endLon")
                            .value = "";

                        selectingStart = true;
                        
                    });
                    
            document
                .getElementById(
                    "currentLocationBtn")
                .addEventListener(
                    "click",
                    () =>
                    {
                        if (!navigator.geolocation)
                        {
                            alert(
                                "Geolocation not supported");

                            return;
                        }

                        navigator.geolocation.getCurrentPosition(
                            position =>
                            {
                                const lat =
                                    position.coords.latitude;

                                const lon =
                                    position.coords.longitude;

                                document
                                    .getElementById(
                                        "startLat")
                                    .value = lat;

                                document
                                    .getElementById(
                                        "startLon")
                                    .value = lon;

                                if (startMarker)
                                {
                                    map.removeLayer(
                                        startMarker);
                                }

                                startMarker =
                                    L.marker([lat, lon])
                                    .addTo(map);

                                startMarker.bindPopup(
                                    "Current Location");

                                startMarker.openPopup(); 
                            

                                map.setView(
                                    [lat, lon],
                                    16);

                                selectingStart = false;
                            },

                            error =>
                            {
                                alert(
                                    "Unable to retrieve location");
                            });
                    });
        });