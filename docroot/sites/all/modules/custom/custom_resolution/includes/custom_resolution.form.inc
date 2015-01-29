<?php
/**
 * Build custom resolution filters form
 */
function custom_resolution_filters_form($form, &$form_state)
{
  $form['field_resolution_number_value'] = array(
    '#title' => t('Resolution number'),
    '#type' => 'textfield',
    '#size' => 30,
    '#default_value' => isset($_GET['field_resolution_number_value']) ?
      $_GET['field_resolution_number_value'] : '',
  );

  // $form['field_resolution_date_value'] = array(
  //   '#title' => t('Resolution date'),
  //   '#tree' => TRUE,
  //   'value' => array(
  //     '#type' => 'date_popup',
  //     '#size' => 20,
  //     '#default_value' => isset($_GET['field_resolution_date_value']) ? 
  //       $_GET['field_resolution_date_value'] : '',
  //     '#date_format' => 'd.m.Y',
  //     '#date_label_position' => 'within',
  //     '#date_year_range' => '-3:+3',
  //     '#process' => 'date_popup_element_process',
  //     '#prefix' => '<div id="edit-field-resolution-date-value-value-wrapper">
  //       <div id="edit-field-resolution-date-value-value-inside-wrapper">',
  //     '#suffix' => '</div></div>',
  //   ),
  // );

  $form['field_resolution_full_name_value'] = array(
    '#title' => t('Resolution full name'),
    '#type' => 'textfield',
    '#size' => 30,
    '#default_value' => isset($_GET['field_resolution_full_name_value']) ?
      $_GET['field_resolution_full_name_value'] : '',
  );

  $form['field_resolution_category_tid'] = array(
    '#title' => t('Resolution category'),
    '#type' => 'select',
    '#options' => _custom_resolution_get_categories(),
    '#default_value' => isset($_GET['field_resolution_category_tid']) ?
      $_GET['field_resolution_category_tid'] : '',
  );

  $form['submit'] = array(
    '#name' => '',
    '#type' => 'submit',
    '#value' => t('Search'),
  );

  $form['#action'] = '';
  $form['#method'] = 'get';
  $form['#after_build'][] = '_custom_resolution_clear_get_parameters';
  $form_state['method'] = 'get';
  return $form;
}

/**
 * Implements hook_form_alter()
 */
function custom_resolution_form_alter(&$form, &$form_state, $form_id)
{
  if ($form_id == 'views_exposed_form') {
    $id = $form['#id'];
    $resolution_form_id_string = 'views-exposed-form-resolutions-block';
    if (strpos($id, $resolution_form_id_string) > -1) {
      hide($form);
    }
  }
}

/**
 * Implements hook_form_FORM_ID_alter()
 */
function custom_resolution_form_resolution_node_form_alter(&$form, &$form_state, $form_id)
{
  $form['supported_parties_filter'] = array(
    '#type' => 'select',
    '#title' => t('Filter delegates by party'),
    '#options' => _custom_resolution_get_parties(),
    '#weight' => $form['field_resolution_analitic']['#weight'] + 0.5,
  );

  $module_path = drupal_get_path('module', 'custom_resolution');
  $script_path = "{$module_path}/scripts/custom_resolution.js";
  drupal_add_js($script_path);

  /* Hide node title field - it will be generated on node saving */
  $form['title']['#access'] = FALSE;
  $form['title']['#required'] = FALSE;
  $form['#validate'][] = '_custom_resolution_validate_resolution_number';
}

/**
 * Get list of parties for filter on resolution node form
 * @return array
 */
function _custom_resolution_get_parties()
{
  $query = db_select('taxonomy_term_data', 'tax');
  $query->fields('tax', array('name', 'vid'));
  $query->condition('tax.vid', 11);
  $result = $query->execute()->fetchCol();
  $parties = array();
  foreach ($result as $party) {
    $parties[$party] = $party;
  }
  return $parties;
}

/**
 * Validation callback for resolution node form
 * Check if resolution number is unique
 */
function _custom_resolution_validate_resolution_number($form, &$form_state)
{
  $values = $form_state['values'];
  $current_nid = $values['nid'];
  $resolution_number_field = $values['field_resolution_number'];
  $resolution_number_value = $resolution_number_field[LANGUAGE_NONE][0]['value'];

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', 'resolution');
  $query->fieldCondition('field_resolution_number', 'value', $resolution_number_value);
  $query->addMetaData('account', user_load(1));
  $result = $query->execute();
  if (!empty($result)) {
    $nids = element_children($result['node']);
    if (!$current_nid || !in_array($current_nid, $nids)) {
      form_error($form['field_resolution_number'], 
        t('Resolution # %number already exists', array(
          '%number' => $resolution_number_value,
        )));
    }
  }
}

/**
 * Get list of resolution categories term
 * @return array
 */
function _custom_resolution_get_categories()
{
  $vocabulary = taxonomy_vocabulary_machine_name_load('resolution_categories');
  $vid = $vocabulary->vid;
  $query = db_select('taxonomy_term_data', 'tax');
  $query->fields('tax', array('tid', 'name', 'vid'));
  $query->condition('tax.vid', $vid);
  $result = $query->execute()->fetchAll();

  $categories = array(
    'All' => t('- All categories -'),
  );
  
  foreach ($result as $row) {
    $tid = $row->tid;
    $name = $row->name;
    $categories[$tid] = $name;
  }

  return $categories;
}

/**
 * After build callback for custom resolution filters form
 */
function _custom_resolution_clear_get_parameters($form)
{
  unset($form['form_token']);
  unset($form['form_build_id']);
  unset($form['form_id']);
  $form['submit']['#name'] = '';
  return $form;
}