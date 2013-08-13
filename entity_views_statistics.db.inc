<?php

function entity_views_statistics_count_view_insert($entity_id, $entity_type) {

  $transaction = db_transaction();
  try {
    if (!isset($_SESSION['entity_views_statistics']) || !isset($_SESSION['entity_views_statistics'][$entity_type]) || !in_array($entity_id, array_keys($_SESSION['entity_views_statistics'][$entity_type]))) {
      global $user;
      $fields = array(
        'entity_id' => $entity_id,
        'uid' => $user->uid,
        'timestamp' => REQUEST_TIME,
        'ip' => ip_address(),
        'entity_type' => $entity_type
      );

      db_insert('entity_views_statistics')
        ->fields($fields)
        ->execute();

      db_merge('entity_views_statistics_counter')
        ->key(array('entity_id' => $entity_id, 'entity_type' => $entity_type))
        ->fields(array('count' => 1))
        ->expression('count', 'count + :inc', array(':inc' => 1))
        ->execute();

      $_SESSION['entity_views_statistics'][$entity_type][$entity_id] = REQUEST_TIME;
    }
  } catch (Exception $e) {
    $transaction->rollback();
    watchdog_exception('entity_views_statistics', $e);
    throw $e;
  }
}


function entity_views_statistics_get_entity_views($entity_id, $entity_type = 'node') {
  $query = db_select('entity_views_statistics_counter', 'c');
  $query->condition('c.entity_id', $entity_id);
  $query->condition('c.entity_type', $entity_type);
  $query->fields('c', array('count'));
  return intval($query->execute()->fetchField());
}

function entity_views_statistics_get_entity_views_multiple($entity_ids, $entity_type = 'node') {
  $query = db_select('entity_views_statistics_counter', 'c');
  $query->condition('c.entity_id', $entity_ids, 'IN');
  $query->condition('c.entity_type', $entity_type);
  $query->fields('c', array('entity_id', 'count'));
  return $query->execute()->fetchAllKeyed();
}

