from django.test import TestCase
from django.template.loader import render_to_string
from django.core.urlresolvers import resolve
from django.http import HttpRequest
from .models import Walkin, Walkout
from .views import home


class WalkinAndWalkoutModelTest(TestCase):
    def test_saving_and_retrieving(self):
        walkin1 = Walkin()
        walkin1.text = "First person"
        walkin1.save()

        saved_walkins = Walkin.objects.all()
        self.assertEqual(saved_walkins[0], walkin1)
        self.assertEqual(saved_walkins.count(), 1)


class SensorViewTest(TestCase):
    def test_can_save_GET_data(self):
        # when walk in happens
        response = self.client.get('/sensor?data=in')

        saved_walkins = Walkin.objects.all()
        self.assertEqual(saved_walkins.count(), 1)
        saved_walkouts = Walkout.objects.all()
        self.assertEqual(saved_walkouts.count(), 0)

        #when walk out happens
        response = self.client.get('/sensor?data=out')

        saved_walkins = Walkin.objects.all()
        self.assertEqual(saved_walkins.count(), 1)
        saved_walkouts = Walkout.objects.all()
        self.assertEqual(saved_walkouts.count(), 1)

    def test_display_data(self):
        response = self.client.get('/sensor?data=in')
        self.assertContains(response, "1 people have walked in.")

    def test_reset(self):
        self.client.get('/sensor?data=in')
        self.client.get('/sensor?data=in')
        self.client.get('/sensor?data=in')

        saved_walkins = Walkin.objects.all()
        self.assertEqual(saved_walkins.count(), 3)

        # after reset
        response = self.client.get('/sensor/reset')

        saved_walkins = Walkin.objects.all()
        self.assertEqual(saved_walkins.count(), 0)
        saved_walkouts = Walkout.objects.all()
        self.assertEqual(saved_walkouts.count(), 0)


class HomePageTest(TestCase):
    def test_root_url_resolves_to_home_page_view(self):
        found = resolve('/')
        self.assertEqual(found.func, home)

    def test_home_page_returns_correct_html(self):
        request = HttpRequest()
        response = home(request)
        expected_html = render_to_string('home.html')
        self.assertEqual(response.content.decode(), expected_html)

    def test_uses_home_template(self):
        response = self.client.get('/')
        self.assertTemplateUsed(response, 'home.html')

# Create your tests here.
# class HomePageTest(TestCase):
#     def test_root_url_resolves_to_home_page_view(self):
#         found = resolve('/')
#         self.assertEqual(found.func, home_page)

#     def test_home_page_returns_correct_html(self):
#         request = HttpRequest()
#         response = home_page(request)
#         expected_html = render_to_string('home.html')
#         self.assertEqual(response.content.decode(), expected_html)


# class ListViewTest(TestCase):
#     def test_display_all_items(self):
#         list_ = List.objects.create()
#         Item.objects.create(text='itemey 1', list=list_)
#         Item.objects.create(text='itemey 2', list=list_)
#         other_list = List.objects.create()
#         Item.objects.create(text='other list 1', list=other_list)
#         Item.objects.create(text='other list 2', list=other_list)

#         response = self.client.get('/lists/%d/' % (list_.id))

#         self.assertContains(response, 'itemey 1')
#         self.assertContains(response, 'itemey 2')
#         self.assertNotContains(response, 'other list 1')
#         self.assertNotContains(response, 'other list 2')

#     def test_uses_list_template(self):
#         list_ = List.objects.create()
#         response = self.client.get('/lists/%d/' % (list_.id))
#         self.assertTemplateUsed(response, 'list.html')


# class NewListTest(TestCase):
#     def test_can_save_POST_request(self):
#         other_list = List.objects.create()
#         correct_list = List.objects
#         self.client.post(
#             '/lists/new',
#             data={'item_text': 'A new list item'}
#         )

#         self.assertEqual(Item.objects.count(), 1)
#         new_item = Item.objects.first()
#         self.assertEqual(new_item.text, 'A new list item')

#     def test_redirects_after_POST(self):
#         response = self.client.post(
#             '/lists/new',
#             data={'item_text': 'A new list item'}
#         )
#         new_list = List.objects.first()
#         self.assertRedirects(response, '/lists/%d/' % (new_list.id))

