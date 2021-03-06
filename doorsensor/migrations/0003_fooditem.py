# -*- coding: utf-8 -*-
# Generated by Django 1.9 on 2016-02-21 02:22
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('doorsensor', '0002_walkout'),
    ]

    operations = [
        migrations.CreateModel(
            name='FoodItem',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=35)),
                ('date', models.CharField(max_length=10)),
                ('expiration', models.CharField(max_length=20)),
                ('calories', models.CharField(max_length=50)),
                ('fat', models.CharField(max_length=200)),
                ('sugar', models.TextField()),
            ],
        ),
    ]
