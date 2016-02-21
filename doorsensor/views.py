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
        new_foodItem = FoodItem(name='potato', date='2016-2-21', expiration='2016-2-28', fat='0.1', sugar='1.7', calories='163')
        new_foodItem.save()
    if data=='onion':
        new_foodItem = FoodItem(name='onion', date='2016-2-21', expiration='2016-3-15', fat='0.1', sugar='0', calories='44')        
        new_foodItem.save()
    if data=='apple':
        new_foodItem = FoodItem(name='apple', date='2016-2-21', expiration='2016-3-2', fat='0.3', sugar='19', calories='95')        
        new_foodItem.save()
    if data=='strawberry':
        new_foodItem = FoodItem(name='strawberry', date='2016-2-21', expiration='2016-2-28', fat='0.1', sugar='3.2', calories='47')        
        new_foodItem.save()
    if data=='blackberry':
        new_foodItem = FoodItem(name='blackberry', date='2016-2-21', expiration='2016-2-28', fat='0.7', sugar='3.9', calories='62')        
        new_foodItem.save()
    if data=='bread':
        new_foodItem = FoodItem(name='bread', date='2016-2-21', expiration='2016-3-21', fat='0.2', sugar='1.5', calories='79')        
        new_foodItem.save()
    if data=='soup':
        new_foodItem = FoodItem(name='soup', date='2016-2-21', expiration='2016-8-21', fat='2.9', sugar='3.8', calories='87')        
        new_foodItem.save()
    if data=='nuts':
        new_foodItem = FoodItem(name='nuts', date='2016-2-21', expiration='2016-4-14', fat='72', sugar='6.3', calories='813')        
        new_foodItem.save()
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