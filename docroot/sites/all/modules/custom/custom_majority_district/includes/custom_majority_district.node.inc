<?php
/**
 * Implements hook_node_presave()
 */
function custom_majority_district_node_presave($node)
{
  $field_district_number = $node->field_district_number;
  $field_district_number_value = $field_district_number[LANGUAGE_NONE][0]['value'];
  $node->title = $field_district_number_value;
}