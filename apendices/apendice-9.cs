using InfluxDB.Client;
using InfluxDB.Client.Writes;

const string orgId = "<ORG_ID>";
const string token = "<TOKEN_AUTORIZACAO>";

    
var client = InfluxDBClientFactory.Create("http://localhost:8086", token);

var pointData = PointData.Measurement("device_status")
    .Tag("motor_dc", "ESP32")
    .Field("current", 0.7d);

var cancellationTokenSource = new CancellationTokenSource();

Console.CancelKeyPress += (sender, e) =>
{
    cancellationTokenSource.Cancel();
    e.Cancel = true;
};


while (!cancellationTokenSource.Token.IsCancellationRequested)
{
    using var write = client.GetWriteApi();
    write.WritePoint(pointData, "motor-data-acquisition", orgId);
    await Task.Delay(1000, cancellationTokenSource.Token);
}
