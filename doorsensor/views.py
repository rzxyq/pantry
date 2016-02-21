from django.shortcuts import render, redirect
from django.http import HttpResponse
from .models import Walkin, Walkout, FoodItem

def home(request):
    context = {
        
    }
    return render(request, 'home.html', context)

def sensor(request):
    data = request.GET.get('data')
    if data=='potato':
        new_foodItem = FoodItem(name='potato', date='2016-2-21', expiration='2016-2-28', fat='0', sugar='100', calories='1000')
        new_foodItem.save()
    # if data=='onion':
    #     new_foodItem = FoodItem(name='onion', )
    #     new_foodItem.save()
    selectees = FoodItem.objects.all()

    context = {
        'foodItems': selectees
    }
    return render(request, 'sensor.html', context)

def reset(request):
    Walkout.objects.all().delete()
    Walkin.objects.all().delete()

    context = {
        
    }
    return redirect('/sensor')


def login(request):
    selectees = FoodItem.objects.filter(Q())
    return render(request, 'selection/select.html', {
        'students': selectees})