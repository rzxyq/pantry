# from django.contrib import admin
# from .models import NewStudent
# from .forms import NewStudentForm


# class NewstudentAdmin(admin.ModelAdmin):
#     list_display = ["__str__", "netid", "year", "major", "selected"]
#     form = NewStudentForm

# admin.site.register(NewStudent, NewstudentAdmin)

from django.contrib import admin
from .models import FoodItem

# Register your models here.
admin.site.register(FoodItem)