<?php

/**
 * Implements hook_form_FORM_ID_alter()
 */
function custom_majority_district_form_majority_district_form_alter(&$form, &$form_state, $form_id)
{
  $form['title']['#access'] = FALSE;
  $form['title']['#required'] = FALSE;
}