<?php
/**
 * Implements hook_block_info()
 */
function custom_resolution_block_info()
{
  $blocks = array();
  $blocks['custom_resolution_filters_block'] = array(
    'info' => t('Resolution filters block'),
    'cache' => DRUPAL_CACHE_GLOBAL,
  );
  return $blocks;
}

/**
 * Implements hook_block_view()
 */
function custom_resolution_block_view($delta = '')
{
  $block = array();
  switch ($delta) {
    case 'custom_resolutions_filters_block' :
      $block['subject'] = t('Resolution filters block');
      $block['content'] = drupal_get_form('custom_resolution_filters_form');
      break;
  }
  return $block;
}