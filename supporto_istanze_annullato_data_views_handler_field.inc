<?php
class supporto_istanze_annullato_data_views_handler_field extends views_handler_field_date {
  function render($values) {
    static $i = 1;
    $value = $this->get_value($values);
    $nid = $values->webform_submissions_node_nid;
    $sid = $values->webform_submissions_node_sid;
    $uid = $values->users_webform_submissions_uid;
    $tid = $values->webform_submissions_node_si_tid;
    $proto = $values->webform_submissions_node_si_protocollo_stato;
    $nodo = node_load($nid);
    $nodata = is_null($values->webform_submissions_node_si_tid);
    if (user_access('annullato') &&
        !($nodata || $proto == 0) &&
        is_null($values->webform_submissions_node_si_annullato_data)
      ) {
      $ass_array = array();
      $ass_array['my_button'] = drupal_get_form('supporto_istanze_cancel_form_'.$i, $sid, $uid, $nodata? 0 : $tid, $nodata? 0 : $value, 'annullato');
      $html = theme('supporto_istanze_views', array ('content' => '', 'assoc' => $ass_array));
      $html = sprintf('<span id="can%d">%s</span>', $sid, $html);
    }
    elseif ($nodata || is_null($value)) {
      $html = '---';
    } else {
      $html = '<img src="' . drupal_get_path('module', 'supporto_istanze') . '/icone/no.png" alt="istanza annullata" title="istanza annullata" /> (' . format_date($value, 'essenziale') . ')';
    }
    ++$i;
    return $html;
  }
}
