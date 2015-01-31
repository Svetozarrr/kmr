<?php
/**
 * Implements template_preprocess_views_view()
 */
function custom_resolution_preprocess_views_view(&$vars)
{
  $view = $vars['view'];
  $view_name = $vars['name'];
  $view_display = $vars['display_id'];
  if ($view_name == 'deputats' || $view_display == 'panel_pane_1') {
    $term = menu_get_object('taxonomy_term', 2);
    $tid = $term->tid;
    $total_votes = _custom_resolution_count_supported_resolutions($tid);
    $total_votes_string = t('Total resolutions supported - @total_votes', 
      array('@total_votes' => $total_votes));
    $vars['header'] = $total_votes_string;
  }
}

function _custom_resolution_count_supported_resolutions($tid)
{
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', 'deputat');
  $query->propertyCondition('status', NODE_PUBLISHED);
  $query->fieldCondition('field_fraction', 'tid', $tid, '=');
  $query->addMetaData('account', user_load(1));
  $result = $query->execute();
  $nodes = $result['node'];
  $nids = array_keys($nodes);
  $total_votes = 0;
  foreach ($nids as $nid) {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'node');
    $query->entityCondition('bundle', 'resolution');
    $query->propertyCondition('status', NODE_PUBLISHED);
    $query->fieldCondition('field_resolution_votes_supported', 
      'target_id', $nid, '=');
    $result = $query->count()->execute();
    $total_votes += $result;
  }
  return $total_votes;
}