<?php
/**
 * Implements hook_node_presave()
 */
function custom_resolution_node_presave($node)
{
  $resolution_number = $node->field_resolution_number[LANGUAGE_NONE][0]['value'];
  $resolution_date = $node->field_resolution_date[LANGUAGE_NONE][0]['value'];
  $resolution_time = time($resolution_date);
  $resolution_date_formatted = format_date($resolution_time, 'short');
  $resolution_title = t('Resolution # @number for @date', array(
    '@number' => $resolution_number,
    '@date' => $resolution_date_formatted,
  ));
  $node->title = $resolution_title;
}
