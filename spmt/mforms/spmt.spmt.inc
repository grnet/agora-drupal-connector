<?php

function _spmt_step1(&$form_state, &$next_step, $params) {
  //define next step, do not set if last step
  $next_step = '_spmt_step2';

  //retrive data from store
  $data = mforms_get_vals('spmt');

  //retrieve saved data
  $savedData = variable_get('spmtData');

  if(!empty($data)) {
    $vals = $data;
  }
  else if(isset($form_state['values'])) {
    $vals = $form_state['values'];
  }

  //edit mode - preload values
  if(isset($params['feed_id']) && isset($savedData)) {
    if(isset($savedData[$params['feed_id']])) {
      $vals['feed_url'] = $savedData[$params['feed_id']]['feed_url'];
      $vals['page'] = $savedData[$params['feed_id']]['page'];
    }
  }

  $form = array();

  $form['feed_url'] = array(
    '#type' => 'textfield',
    '#title' => 'Feed url',
    '#required' => TRUE,
    '#default_value' => isset($vals['feed_url']) ? $vals['feed_url'] : NULL,
  );

  $form['page'] = array(
    '#type' => 'textfield',
    '#title' => 'Page to render the feed',
    '#required' => TRUE,
    '#default_value' => isset($vals['page']) ? $vals['page'] : NULL,
  );

  // keep the feed_id from params
  if(isset($params['feed_id'])) {
    $form['feed_id'] = array(
      '#type' => 'hidden',
      '#title' => 'feed_id',
      '#default_value' => $params['feed_id']
    );
  }

  return $form;
}

function _spmt_step1_validate($form, &$form_state) {
  if(empty($form_state['values']['feed_url'])) {
    form_set_error('feed_url', 'The feed url must not be empty');
  } else if(empty($form_state['values']['page'])) {
    form_set_error('page', 'The page to render the feed must not be empty');
  } else {
    $result = drupal_json_decode(shell_exec("curl ".$form_state['values']['feed_url']." --insecure"));
    if(isset($result['status']) && $result['status']) {
      // 404 or some other error
      form_set_error('feed_url', 'There is a problem with the feed url');
    }
  }
}

function _spmt_step2(&$form_state, &$next_step, $params) {
  //define next step, do not set if last step
  $next_step = '_spmt_step3';

  //retrive data from store
  $data = mforms_get_vals('spmt');

  //retrieve saved data
  $savedData = variable_get('spmtData');

  if(!empty($data)) {
    $vals = $data;
  }
  else if(isset($form_state['values'])) {
    $vals = $form_state['values'];
  }

  $request_url = $vals['feed_url'];

  $converted_keys = getStep2Data($request_url);

  //edit mode - preload values
  if(isset($params['feed_id']) && isset($savedData)) {
    if(isset($savedData[$params['feed_id']])) {
      $vals['fields'] = array_flip($savedData[$params['feed_id']]['fields']);
    }
  }

  $form = array();

  $form['selected_fields'] = array(
    '#type' => 'multiselect',
    '#title' => t('Select the keys you want to be visible in the page'),
    '#properties' => array(),
    '#options' => $converted_keys,
    '#default_value' => (isset($vals['fields'])) ? $vals['fields'] : array(),
    '#multiple' => TRUE,
    '#size' => 15,
    //'#required' => FALSE,
  );

  $form['#attached']['css'] = array(
    drupal_get_path('module', 'multiselect') . '/multiselect.css',
  );

  $form['#attached']['js'] = array(
    drupal_get_path('module', 'multiselect') . '/multiselect.js',
  );

  return $form;
}

function _spmt_step2_validate($form, &$form_state) {
  if(empty($form_state['values']['selected_fields'])) {
    form_set_error('selected_fields', 'You must select at least one field');
  }
}

function _spmt_step3(&$form_state, &$next_step, $params) {
  //define next step, do not set if last step
  $next_step = '_spmt_step4';

  //retrive data from store
  $data = mforms_get_vals('spmt');

  //retrieve saved data
  $savedData = variable_get('spmtData');

  if(!empty($data)) {
    $vals = $data;
  }
  elseif(isset($form_state['values'])) {
    $vals = $form_state['values'];
  }

  $selected_fields = array();
  foreach($vals['selected_fields'] as $k) {
    $selected_fields[$k] = $k;
  }

  //edit mode - preload values
  if(isset($params['feed_id'])
      && isset($savedData)
      && isset($savedData[$params['feed_id']])
  ) {
    $saved_field_names = $savedData[$params['feed_id']]['fields'];
    foreach($selected_fields as $field)
      $selected_fields[$field] = isset($saved_field_names[$field]) ?
                                 $saved_field_names[$field] : $field;
  }

  $form = array();

  foreach($selected_fields as $k => $v) {
    $form['field__'.$k.'__label'] = array(
      '#type' => 'hidden',
      '#title' => 'field__'.$k.'__label',
      '#required' => TRUE,
      '#default_value' => $k,
    );
    $form['field__'.$k.'__value'] = array(
      '#type' => 'textfield',
      '#title' => $k,
      '#default_value' => $v,
    );
  };

  return $form;
}

function _spmt_step4(&$form_state, &$next_step, $params) {
  //define next step, do not set if last step

  //retrive data from store
  $data = mforms_get_vals('spmt');

  if(!empty($data)) {
    $vals = $data;
  }
  elseif(isset($form_state['values'])) {
    $vals = $form_state['values'];
  }

  $vals1 = mforms_get_vals('spmt', '_spmt_step1');

  $form = array();

  $final_fields = getStep3Fields($vals);

  $form['basic_info'] = array(
    '#type' => 'fieldset',
    '#title' => 'Basic info'
  );

  $form['visible_fields'] = array(
    '#type' => 'fieldset',
    '#title' => 'Visible Fields'
  );

  $form['basic_info']['feed_url'] = array(
    '#type' => 'item',
    '#title' => 'Feed url',
    '#description' => $vals1['feed_url'],
  );

  foreach($final_fields as $key => $value) {
    $form['visible_fields'][$key] = array(
      '#type' => 'item',
      '#title' => $key,
      '#description' => $value,
    );
  }

  return $form;
}

function _spmt_step4_submit($form, &$form_state) {

  $vals1 = mforms_get_vals('spmt', '_spmt_step1');
  $vals3 = mforms_get_vals('spmt', '_spmt_step3');
  $final_fields = getStep3Fields($vals3);

  $new_feed_data = array(
    'feed_url' => $vals1['feed_url'],
    'page' => $vals1['page'],
    'fields' => $final_fields
  );

  $savedData = variable_get('spmtData');

  //edit mode - preload values
  if(isset($vals1['feed_id']) && isset($savedData[$vals1['feed_id']])) {
    $savedData[$vals1['feed_id']] = $new_feed_data;
  } else if(isset($savedData) && sizeof($savedData) > 0) {
    $savedData[] = $new_feed_data;
  } else {
    $savedData = array();
    $savedData[] = $new_feed_data;
  }

  // lastly, save data
  variable_set('spmtData', $savedData);

  //clear session
  mforms_clean('spmt');

  //redirect
  drupal_goto('/admin/config/spmt');

}

function getStep3Fields($vals) {

  // get only the field__ items
  $fields = array_filter($vals, function($value, $key) {
    return (is_string($key) && substr($key, 0, 7) === 'field__');
  }, ARRAY_FILTER_USE_BOTH);

  $labels = array_filter($fields, function($value, $key) {
    return (substr($key, -7) === '__label');
  }, ARRAY_FILTER_USE_BOTH);

  $values = array_diff_assoc($fields, $labels);

  $final_fields = array();

  foreach($labels as $key => $value) {
    $partial = substr($key, 0, -7);
    $item = array($value => $values[$partial.'__value']);
    $final_fields += $item;
  }

  return $final_fields;
}

function getStep2Data($request_url) {

  //$result = drupal_http_request($request_url, array('Content-Type' => 'application/json'), 'GET', '', 3);
  $result = drupal_json_decode(shell_exec("curl ".$request_url." --insecure"));

  $keys = array();

  if(sizeof($result) > 0) {
    $item = $result[0];
    foreach($item as $key => $value) {
      array_push($keys, $key);
    }
  }

  $ext_keys = array();

  foreach($keys as $key) {
    if(substr($key, -4) === '_ext') {
      array_push($ext_keys, $key);
    }
  }

  // filter out flat relations
  $final_keys = array_filter($keys, function($k) use ($ext_keys) {
    return !in_array($k.'_ext', $ext_keys);
  });

  $converted_keys = array();

  foreach($final_keys as $key) {
    $converted_keys[$key] = $key;
  }

  return $converted_keys;
}
