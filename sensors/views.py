from django.shortcuts import render

from rest_framework import generics
from .models import SensorData
from .serializers import SensorDataSerializer
from django.core.serializers import serialize

from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework import status
from django.views.decorators.csrf import csrf_exempt
from django.utils.decorators import method_decorator
from .serializers import SensorDataSerializer


@method_decorator(csrf_exempt, name="dispatch")
class SensorDataCreateView(APIView):
    def post(self, request, format=None):
        # Print raw body
        print("RAW BODY:", request.body)
        print("CONTENT TYPE:", request.content_type)

        # Try parsing JSON manually
        import json

        try:
            data = json.loads(request.body)
        except Exception as e:
            print("JSON PARSE ERROR:", e)
            return Response({"error": "Invalid JSON"}, status=400)

        serializer = SensorDataSerializer(data=data)
        if serializer.is_valid():
            serializer.save()
            print("SAVED:", serializer.data)
            return Response({"status": "success"}, status=status.HTTP_201_CREATED)
        print("SERIALIZER ERRORS:", serializer.errors)
        return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)


class SensorDataListView(generics.ListAPIView):
    queryset = SensorData.objects.all().order_by("-created_at")[:50]
    serializer_class = SensorDataSerializer


from django.shortcuts import render
from .models import SensorData
from .serializers import SensorDataSerializer


def dashboard(request):
    data_qs = SensorData.objects.order_by("-created_at")[:20]
    data_json = serialize(
        "json",
        data_qs,
        fields=("temperature", "humidity", "pressure", "air_quality", "created_at"),
    )
    return render(request, "sensors/dashboard.html", {"data_json": data_json})
