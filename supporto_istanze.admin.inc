<?php
/**
 * @file
 * settings file
 */
 
/**
 * Settings form.
 */
function supporto_istanze_admin_settings_form() {
  $my_nodes = array();
  node_types_rebuild();
  $node_types = node_type_get_types();
  foreach ($node_types as $node_type) {
    $my_nodes[$node_type->type] = $node_type->type;
  }

  $form['supporto_istanze_content1'] = array(
    '#type' => 'fieldset',
    '#title' => 'Tipi di contenuto',
  );
  $form['supporto_istanze_content1']['supporto_istanze_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => 'tipi di contenuto usati per le istanze',
    '#default_value' => variable_get('supporto_istanze_node_types', array('istanze_del_personale' => 'istanze_del_personale')),
    '#options' => $my_nodes,
    '#multiple' => TRUE,
  );
  $form['supporto_istanze_content2'] = array(
    '#type' => 'fieldset',
    '#title' => 'Email della segreteria',
  );
  $form['supporto_istanze_content2']['supporto_istanze_email'] = array(
    '#type' => 'textfield',
    '#title' => t('E-mail address'),
    '#maxlength' => 254,
    '#description' => 'indirizzo e-mail valido',
    '#required' => TRUE,
    '#default_value' => variable_get('supporto_istanze_email', ''),
  );
  $form['#submit'][] = '_supporto_istanze_acquisisci_reset_field';
  return system_settings_form($form);
}