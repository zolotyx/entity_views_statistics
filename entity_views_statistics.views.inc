<?php
/**
 * Implements hook_views_data().
 *
 * works just for nodes
 */
function entity_views_statistics_views_data() {
  $data = array();

  $data['entity_views_statistics_counter']['table']['group'] = t('Entity views count');

  $data['entity_views_statistics_counter']['table']['base'] = array(
    'field' => 'entity_id',
    'title' => t('Entity views count'),
    'help' => t('This table is containing the data about entity views count.'),
    'weight' => -10,
  );

  $data['entity_views_statistics_counter']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'entity_id',
    ),
  );

  $data['entity_views_statistics_counter']['count'] = array(
    'title' => t('Entity views count'),
    'help' => t('Entity views count.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Example plain text field.
  $data['entity_views_statistics_counter']['entity_type'] = array(
    'title' => t('Entity type'),
    'help' => t('Type of the entity'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE, // This is use by the table display plugin.
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}