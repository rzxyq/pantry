from django.db import models


class Walkin(models.Model):
    timestamp = models.DateTimeField(auto_now_add = True, auto_now = False)
    text = models.TextField(default='')

    def __str__(self):
        return self.timestamp

class Walkout(models.Model):
    timestamp = models.DateTimeField(auto_now_add = True, auto_now = False)
    text = models.TextField(default='')
    
    def __str__(self):
        return self.timestamp


class FoodItem(models.Model):

   # <td>{{foodItems.name}}</td>
   #                  <td>{{foodItems.date}}</td>
   #                  <td>{{foodItems.expiration}}</td>
   #                  <td>{{foodItems.calories}}</td>
   #                  <td>{{foodItems.fat}}</td>
   #                  <td>{{foodItems.sugar}}</td>
    name = models.CharField(max_length=35)
    date = models.CharField(max_length=10)
    # hometown = models.CharField(max_length=35)
    expiration = models.CharField(max_length=20)
    calories = models.CharField(max_length=50)
    fat = models.CharField(max_length=200)
    sugar = models.CharField(max_length=200)

    def __str__(self):
        return self.name
