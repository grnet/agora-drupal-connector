# Agora Drupal Connector

### Description


This drupal module allows the administrator to create multiple agora feeds, choose which fields to render and create pages to render the data feeds. The administrator provides a valid Agora API Feed, selects which fields wants to be visible and specifies a new url in order for ReactJS app to render the defined selections.

This module is working with a dependency of [agora-catalogue-react-view](https://github.com/grnet/agora-catalogue-react-view)

### Installation

1) Install directly from source

  - Clone the repo or download a release
  - Copy the files inside `files/all/modules` directory of the drupal installation.
  - Enable the module from the `modules` page inside drupal admin (under the namespace `Grnet - Agora`).

2) Install from drush
  - From the directory that you run drush commands, run `drush en agora_sp` (and pressing `y` where requested to download and enable the dependencies) to download, install and enable the module.

### Usage

1) Create a new feed

  - Navigate to `admin/config/agora_sp` or click `Configuration/Agora Service Portfolio` from the administration menu.
  - Click `Add a new feed` to create a new feed, providing a valid Agora API Feed, declaring an unused drupal url in order to render the feed  and selecting the fields to be shown in the render page.
  - Clear all caches (or run `drush cc all`).
  - Navigate to the previously declared url.

2) Edit/Delete a feed
  - Navigate to `admin/config/agora_sp` or click `Configuration/Agora Service Portfolio` from the administration menu.
  - In the `Manage Agora Feeds` you can see all the created feeds. You can click `Edit` to edit the field, or `Delete` to remove it.
  - Clear all caches (or run `drush cc all`).

*Note*

The easiest way to clear caches in drupal from the administration menu, is to navigate to `Administration > Configuration > Development > Performance`

### Updating the React app

Whenever there is a new version of the React UI app, the steps to update and bump the drupal module version is as follows:

  - Clone the repo of React UI and run `yarn && yarn build`
  - From the output build folder of the above command, copy the `build/static/js/main.XXX.js` and paste it in this repo inside the `js` directory, with the name `agora_sp-ui.min.js`
  - Update the Changelog and commit
  - Git tag to bump version and push changes to remote(s)

### Funding
The work represented by this software was partially funded by
* EOSC-Hub project  European Union (EU) Horizon 2020 program under Grant number 77753642. 
* EUDAT2020  European Union’s H2020  Program under Contract No. 654065.
* EUDAT  Framework Programme 7 under Contract No. 283304.
