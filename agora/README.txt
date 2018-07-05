Description
-------
The Agora module defines an administration Form and creates a drupal page for every Agora API Feed you provide.

You can provide an API feed, and it will gather all the keys from the specific API so the user can select which ones to use, provide labels for every field, order them and then provide them to a React rendering app to show a listing with these fields.

Install
-------
Installing the Agora module is simple:

1) Copy the agora directory to the modules directory in your installation, or install it through Drush CLI Tool ( drush dl agora )

2) Enable the module using the Modules administration page (/admin/modules) or through Drush CLI Tool ( drush en agora )

3) Navigate to `/admin/config/agora` and start creating Agora API Feeds.
