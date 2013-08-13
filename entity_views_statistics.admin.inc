<?php

/**
 * Admin form.
 */
function entity_views_statistics_admin_settings_form($form, &$form_state) {
  // Get node types that were checked on admin settings form.
  $options_entity_types = entity_views_statistics_get_checked_node_types();

  $form['entity_views_statistics_entity_types_options'] = array(
    '#title' => t('Entity types'),
    '#description' => t('Choose entity types to count views.'),
    '#type' => 'checkboxes',
    '#options' => $options_entity_types,
    '#default_value' => variable_get('entity_views_statistics_entity_types_options', array()),
  );
  // Get user roles options.
  $form['entity_views_statistics_user_roles_options'] = array(
    '#title' => t('User roles'),
    '#description' => t('Choose user roles to count node views for.'),
    '#type' => 'checkboxes',
    '#options' => user_roles(),
    '#default_value' => variable_get('entity_views_statistics_user_roles_options', array()),
  );
  return system_settings_form($form);
}

/**
 * Get node types options.
 *
 * @return
 *   Associative array of options.
 */
function entity_views_statistics_get_checked_node_types() {
  $options = array();
  // All node types on site.
  foreach (entity_get_info() as $type => $entity) {
    $options[$type] = $entity['label'];

  }
  return $options;
}

