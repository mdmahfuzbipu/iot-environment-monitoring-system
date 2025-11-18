from django.db import models


class SensorData(models.Model):
    temperature = models.FloatField()
    humidity = models.FloatField()
    air_quality = models.FloatField()
    pressure = models.FloatField(null=True, blank=True)
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return f"{self.created_at} - {self.temperature}°C"
