<?php

/**
 * Check whether comments are enabled for this node.
 */
function ds_contrib_facebook_comments_enabled($node) {
  if (!facebook_comments_is_enabled($node->type)) return FALSE;
  $comments = ds_contrib_facebook_comments_settings($node);
  return isset($comments->enabled) && $comments->enabled;
}

/**
 * Fetch comments settings for node.
 */
function ds_contrib_facebook_comments_settings($node) {
  $cache = &drupal_static(__FUNCTION__);
  if (!isset($cache[$node->nid])) {
    $cache[$node->nid] = db_select('facebook_comments', 'f')
      ->fields('f', array('enabled', 'amount'))
      ->condition('f.nid', $node->nid, '=')
      ->execute()
      ->fetchObject();
  }
  return $cache[$node->nid];
}
