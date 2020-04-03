<?php
/**
 * @file
 * Panels pane to display a ting collection.
 */

$plugin = array(
  'title' => t('Ting series'),
  'description' => t('Ting object series content type'),
  'single' => TRUE,
  'content_types' => array('ting_object'),
  'render callback' => 'ting_series_content_type_render',
  'required context' => new ctools_context_required(t('Ting object'), 'ting_object'),
  'category' => t('Ting'),
);

/**
 * Implements hook_ID_content_type_render().
 */
function ting_series_content_type_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $object = isset($context->data) ? ($context->data) : NULL;
  //$object = menu_get_object('ting_object', 2);
  file_put_contents("/var/www/drupal7vm/drupal/debug/series4.txt", print_r($object->reply->getSeriesDescription(), TRUE), FILE_APPEND);
  file_put_contents("/var/www/drupal7vm/drupal/debug/series5.txt", print_r($object->reply->getSeriesTitles(), TRUE), FILE_APPEND);
  
  $query = ting_series_is_series ($object);
   file_put_contents("/var/www/drupal7vm/drupal/debug/series6.txt", print_r($query, TRUE), FILE_APPEND);
  if (isset($query)) {
    $cid = md5('new' . $query['query']);
file_put_contents("/var/www/drupal7vm/drupal/debug/series30.txt", print_r("Ramt", TRUE), FILE_APPEND);
    if ($cache = cache_get($cid, 'cache_ting_series')) {
      $items = $cache->data;
      $offset = -1;
    } else {
      $items = array();
      $offset = 0;
    }


    $carousels[] = array(
      '#type' => 'ding_carousel',
      '#title' => $query['query'],
      '#path' => 'series/ting/ajax/' . $query['type'] . '/' . urlencode($query['query']),
      '#items' => $items,
      '#offset' => $offset, 
      // Add a single placeholder to fetch more content later if there is more
      // content.
      '#placeholders' => 1, 
    );


    $block->title = '';
    $block->content = array(
      '#type' => 'ding_tabbed_carousel',
      '#title' => $query,
      '#tabs' => $carousels,
    );
  
  }
  return $block;
}

/**
 * Implements hook_ID_content_type_edit_form().
 */
function ting_series_ting_series_content_type_edit_form($form, &$form_state) {
  return $form;
}

