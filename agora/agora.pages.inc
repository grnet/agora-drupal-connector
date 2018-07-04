<?php

function agora_wizard_page($feed_id = NULL) {

  $description = '<h1>Agora Configuration';

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
    'mform' => drupal_get_form('agora_form', $params),
  );
}

function agora_form($form, &$form_state, $params) {
  return mforms_build('agora', '_agora_step1', $form_state, $params);
}

function agora_form_validate($form, &$form_state) {
  mforms_validate('agora', $form, $form_state);
}

function agora_form_submit($form, &$form_state) {
  mforms_submit('agora', $form, $form_state);
}
