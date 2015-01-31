<?php
/**
 * Implements hook_node_presave()
 */
function custom_majority_district_node_presave($node)
{
  dpm($node);
}