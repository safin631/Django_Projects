from django.urls import path
from . import views
urlpatterns=[
    path("",views.show,name='index'),
    path("home/",views.show,name='home'),
    path("register/",views.registerpage, name='register')


]
