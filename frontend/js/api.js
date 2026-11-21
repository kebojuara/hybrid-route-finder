async function requestRoute(
    startLat,
    startLon,
    endLat,
    endLon)
{
    const response =
        await fetch(
            "http://localhost:8080/route",
            {
                method: "POST",

                headers:
                {
                    "Content-Type":
                        "application/json"
                },

                body: JSON.stringify(
                {
                    startLat,
                    startLon,
                    endLat,
                    endLon
                })
            });

    return await response.json();
}