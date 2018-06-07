<?php

function spmt_wizard_page($feed_id = NULL) {

  $description = '<h1>this is a description for spmt form';

  $params = array();
  if(isset($feed_id)) {
    $params = array(
      'feed_id' => $feed_id,
    );
  }

  return array(
    'message' => array(
      '#markup' => $description,
    ),
    'mform' => drupal_get_form('spmt_form', $params),
  );
}

function spmt_form($form, &$form_state, $params) {
  return mforms_build('spmt', '_spmt_step1', $form_state, $params);
}

function spmt_form_validate($form, &$form_state) {
  mforms_validate('spmt', $form, $form_state);
}

function spmt_form_submit($form, &$form_state) {
  mforms_submit('spmt', $form, $form_state);
}
