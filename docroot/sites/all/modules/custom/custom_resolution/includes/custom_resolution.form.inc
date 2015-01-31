<?php
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