from django.shortcuts import render

# Create your views here.
from django.http import HttpResponse

def show(request):
    return render(request,'index.html')

def aboutpage(request):
    return render(request,'about.html')

def registerpage(request):
    return render(request,'register.html')
