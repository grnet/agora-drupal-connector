# Agora Drupal Connector

### Description

This drupal module allows the user to render a service catalogue listing of the services provided by `eudat.eu`. The user specifies a new url in order for the ReactJS application to load.

This module is working with a dependency of [agora-catalogue-react-view](https://github.com/grnet/agora-catalogue-react-view)

### Installation

1) Install directly from source

  - Clone the repo or download a release
  - Copy the directory `react_catalogue` inside `files/all/modules` directory of the drupal installation.
  - Enable the module from the `modules` page inside drupal admin (under the namespace `Grnet`).
  - Navigate to `admin/config/react_catalogue` (or click the configure button from the `modules` page) in order to declare a page url for the application to load.
  - Clear all caches (or run `drush cc all` from the cmd line).
  - Navigate to the previously declared url.

**NOTE**: You must first declare a page inside the `admin/config/react_catalogue` in order for the plugin to work.

This module creates a new page for now, it does not provide a block.
