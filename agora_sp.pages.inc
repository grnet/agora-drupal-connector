<?php

function agora_sp_wizard_page($feed_id = NULL) {

  $description = '<h1>Agora SP Configuration';

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
    'mform' => drupal_get_form('agora_sp_form', $params),
  );
}

function agora_sp_form($form, &$form_state, $params) {
  return mforms_build('agora_sp', '_agora_sp_step1', $form_state, $params);
}

function agora_sp_form_validate($form, &$form_state) {
  mforms_validate('agora_sp', $form, $form_state);
}

function agora_sp_form_submit($form, &$form_state) {
  mforms_submit('agora_sp', $form, $form_state);
}
