from django.urls import path
from .views import SensorDataCreateView, SensorDataListView

urlpatterns = [
    path("data/", SensorDataCreateView.as_view(), name="sensor-data-create"),
    path("data/latest/", SensorDataListView.as_view(), name="sensor-data-list"),
]
