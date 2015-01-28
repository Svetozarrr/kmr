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
    case 'custom_resolution_filters_block' :
      $block['subject'] = t('Resolution filters block');
      $block['content'] = _custom_resolution_get_exposed_filters();
      break;
  }
  return $block;
}

function _custom_resolution_get_exposed_filters()
{
  $view = views_get_view('resolutions');
  $view->set_display('block_1');
  $view->init_handlers();
  $exposed_form_state = array(
    'view' => &$view,
    'display' => &$view->display['block_1'],
    'exposed_form_plugin' =>$view->display_handler->get_plugin('exposed_form'),
    'method' => 'get',
    'rerender' => TRUE,
    'no_redirect' => TRUE,
    'always_process' => TRUE,
    'visible' => TRUE,
  );
  $form = drupal_build_form('views_exposed_form', $exposed_form_state);
  $rendered_form = render($form);
  return $rendered_form;
}